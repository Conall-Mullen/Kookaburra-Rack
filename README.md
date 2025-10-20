# Kookaburra VCV Rack Module

- Download the Rack SDK ([Windows x64](https://vcvrack.com/downloads/Rack-SDK-latest-win-x64.zip) / [Mac x64](https://vcvrack.com/downloads/Rack-SDK-latest-mac-x64.zip) / [Mac ARM64](https://vcvrack.com/downloads/Rack-SDK-latest-mac-arm64.zip)/ [Linux x64](https://vcvrack.com/downloads/Rack-SDK-latest-lin-x64.zip))

- In your terminal, run

  `export RACK_DIR=<Rack SDK folder>`

- To specify the absolute path of the extracted Rack SDK. You may wish to add this line to your ~/.bashrc or other shell environment, so you don’t have to define it every time you open a terminal. Method 2 in [this](https://www.alibabacloud.com/blog/a-guide-on-environment-variable-configuration-in-linux_598423) tutorial should help

- Clone this repo:

  `git clone https://github.com/Conall-Mullen/Kookaburra-Rack.git`

- Then build the plugin which should then be accessible in VCV Rack user folder (You will probably have to restart VCV Rack if it's open)

  `make install`
