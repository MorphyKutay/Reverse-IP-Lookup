# Reverse IP Lookup Program

This Tool performs a reverse IP lookup for a specified domain name to identify other domain names hosted on the same IP address. It leverages the ViewDNS API to query the IP address and retrieve a list of associated domains, which are then saved to an output file.

## Requirements

Before running the program, ensure the following libraries are installed:

- [libcurl](https://curl.haxx.se/libcurl/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [Viewdns API Key](https://viewdns.info/)

### Install on Linux (Ubuntu):
```bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install nlohmann-json3-dev
```

### Install on macOS:

```bash
brew install curl
brew install nlohmann-json


```

### Usage
`$./reverseip -u google.com -a <apikey> -o output.txt `


### Parameters:

```
1-) -u <domain>: The domain name (e.g., google.com)
2-) -a <apikey>: ViewDNS API key
3-) -o <output.txt>: The name of the output file (e.g., output.txt)
```
### License

[GNU General Public License (GPL)](https://github.com/MorphyKutay/Reverse-IP-Lookup/blob/main/LICENSE)

### Screenshot

![screen](https://github.com/MorphyKutay/Reverse-IP-Lookup/blob/main/reverse.png)


