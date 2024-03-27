## Game Of Life -  
### Installation Instructions
##### Only for Ubuntu

#### Dependencies
To install the necessary libraries, enter the command<br>
```sudo apt install libsdl2-dev```
#### Sourse files
To install the application, you must first download the source files<br>
Go to the directory where you want to download the source files and enter the command<br>
``` wget https://github.com/VtripleG/GameOfLifeSDL2/archive/master.tar.gz ```<br>
Next, you need to unpack the archive with the source files<br>
``` tar -xf master.tar.gz ```<br>
#### Build
Then we execute a sequence of commands<br>
``` cmake cmake -S GameOfLifeSDL2-master/ -B GameOfLife/ && cd GameOfLife/ && make ```<br>
**COMPLITE**

#### Run
For default run<br>
``` ./GameOfLife ```<br>
For run with parameters<br>
``` ./GameOfLife <width> <height> <speed> ```<br>
Or<br>
``` ./GameOfLife <speed> ```<br>
\<width\> - width of game board. **Can be from 5 to 20**<br>
\<height\> - height of game board. **Can be from 5 to 20**<br>
\<speed\> - game speed. **Can be from 1 to 5**<br>

