# Gold Miner

Gold Miner is a 2D game written in SFML/C++.

## Setup

Clone the repository and run ```install``` script

```bash
$ git clone https://github.com/sliziky/Gold-Miner.git
$ cd Gold-Miner
$ chmod u+x install
$ ./install
```

## Usage
To run game
```bash
$ cd build
$ cd src
$ ./GoldMiner
```
## Troubleshooting
### 1. Forgot to add permissions 
```bash
$ bash: ./SCRIPT_NAME: Permission denied
```
#### Solution 
```
$ chmod u+x SCRIPT_NAME
```

### 2. Bad interpreter error
```bash
$ bash: ./run: /bin/bash^M: bad interpreter: No such file or directory
```
#### Solution
```
$ sudo apt-get install dos2unix
$ dos2unix install
$ dos2unix run
```

### 3. No CMAKE_CXX_COMPILER could be found
```bash
$ No CMAKE_CXX_COMPILER could be found.
```
#### Solution
```bash
$ sudo apt-get install g++
```
## Game Sample
![Alt Text](https://media.giphy.com/media/7NGa55eqCUPP7Nks9x/giphy.gif)



