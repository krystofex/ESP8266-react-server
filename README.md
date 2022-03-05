# React server on ESP8266

## Setup
1. build React app 
    ```bash
    cd react-app
    npm install
    npm run build
    cp -r ./buid ../data/
    cd ..
    ```
2. Copy and edit config file
    ```bash
    cp ./include/config.h.example ./include/config.h
    nano ./include/config.h
    ```
3. Upload files and code 
    ```bash
    pio run -t buildfs
    pio run -t uploadfs 
    pio run
    pio run --target upload
    ```
4. Check for server address in serial monitor

## Purpose

### Arduino program
1. simple API examples
2. React server

### React app
1. control LED via API