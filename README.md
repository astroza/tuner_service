# tuner_service
Monkey duda service for V4L2 Tuners
## Usage
### Set frequency
 curl -XPOST -d89.7 http://host:port/tuner/frequency
### Get frequency
 curl -XGET http://host:port/tuner/frequency
 
### Set volume
 curl -XPOST -d100.0 http://host:port/tuner/volume
### Get volume
 curl -XGET http://host:port/tuner/volume
