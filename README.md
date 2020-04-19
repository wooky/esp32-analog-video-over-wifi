Analog Composite Video Transmission over Wi-Fi for ESP32
========================================================

Goals
-----
* Transmit a NTSC signal captured by a CCTV camera over Wi-Fi to a central monitoring server
* Reduce bandwidth for transmission, as a raw BT.601/BT.656 stream requires a bandwidth of 216Mbps, which is unacceptable even over LAN
* Minimize costs per converter/transmitter

Equipment
---------
* Any NTSC composite camera - in my case, I have a handful of Bosch VDC-455V04-20 CCTV cameras
* NTSC-M digital video decoder - whatever the cheapest you can find on eBay, e.g.
    * TW9900
    * AK8859VN
    * GM7150BC
* ESP32 module **with >=1MB pSRAM** - ESP32's SRAM is not big enough to store even a single frame
* Various power supplies and/or voltage regulators required to power the decoder/ESP32
* Additional components as required by the decoder/ESP32

### Video Decoder Requirements
 * Compliant BT.601 output
 * Has I²C interface (AKA two wire serial interface)
 * Can output synced, hsync, vsync signals
 * Ability to remove hsync/vsync, SAV/EAV signals from transmission

Interface Pinout
----------------
```
+-----------+
|       AIN | <---- () Analog NTSC composite video
|           |
|           |       +---------------+
|      SCLK | <---- | I2C_SCL       |
|      SDAT | <---> | I2C_SDA       |
|           |       |               |
|      DCLK | ----> | I2S0I_WS_in   |
| SYNC (EN) | ----> | I2S0_H_ENABLE |
|     HSYNC | ----> | I2S0_H_SYNC   |
|     VSYNC | ----> | I2S0_V_SYNC   |
| DATA[7:0] | ----> | I2S0I_Data_in |
+-----------+       +---------------+
```

Order of Operations
-------------------
1. Set up logging
2. Set up Wi-Fi
3. Set up I²S transfer
    * This includes allocating enough DMA RAM for one line of data
    * Invert HSYNC/VSYNC/enable signals in software if necessary
4. Allocate enough RAM on pSRAM for one complete frame
5. Set up decoder
6. Wait until client has connected
7. Start decoder
8. Wait until signal is syncronized so data transfer can begin
9. When HSYNC is active:
    * Copy the line data to pSRAM, swapping BT.601's `CbY0CrY1` data order to the JPEG library's `Y0CbY1Cr` expected input
    * Remember that since the signal is interlaced, copy into rows 1, 3, 5, ..., and then to rows 2, 4, 6, ...
    * In the event this copying takes longer than HSYNC, allocate a second DMA RAM chunk for the next line
10. When VSYNC is reached, repeat step 7, but prepare to copy field 2 (even rows)
11. On the next VSYNC:
    * Call the JPEG library to convert the resulting YUV frame to JPEG
    * Transfer result, along with headers, over Wi-Fi
    * If this takes longer than the VBLANK period, offload these tasks to the second core.
    * If the conversion is not done before end of VBLANK period, create another buffer for the frame on pSRAM
12. Go to step 8, waiting until VBLANK is done