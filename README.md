# tuner_service
Monkey duda service for V4L2 Tuners
## Usage
* Set frequency
```bash
curl -XPOST -d89.7 http://host:port/tuner/frequency
```
* Get frequency
```bash
curl -XGET http://host:port/tuner/frequency
```
* Set volume
```bash
curl -XPOST -d100.0 http://host:port/tuner/volume
```
* Get volume
```bash
curl -XGET http://host:port/tuner/volume
```
