# PMSD interface module driver for Raspberry PI 3B
This is a driver module for built to facilitate the communication between highte level user applications and the PMSD interface module for the Raspberry PI 3B. This project comes with a sample user application to demonstrate the use of the driver.

**DISCLAIMER:** The driver has been tested only on the Raspberry Pi 3B running *Linux raspberrypi 4.19.57-v7+* and may not work on any non Raspbian OS. Test at your own risk.

# Using the driver
## Compiling the driver 
To compile the driver module alone run the following command in the build directory.
 ```
 make PMSDIMD
 ```

## Intalling the driver
To load the driver and generate the driver file automatically run the following command in the build directory.
```
sudo make install
````

## Unintalling the driver
To unload the driver and remove the driver file automatically run the following command in the build directory.
```
sudo make uninstall
````

# Running the sample user application
The sample user application is provided as a referance for developing user applications for the PMSD interface module through the use of th provided driver.

**DISCLAIMER:** The user application has only been tested on the Raspberry Pi 3B running *Linux raspberrypi 4.19.57-v7+* and may not work on any non Raspbian OS. Test at your own risk.

## Compiling the user application and the driver
First compile both the user application and the driver by running `make` in the build directory.

# For Devs
**Important note:** Please remember to run `make clean` in the build directory before staging and pushing to the repository.

## Testing the driver
To compile the driver module run the following command in the build directory.
```
make PMSDIMD
```

### Without the bash script
#### Loading the driver
To load the driver module without the use of the script use the following command:
```
sudo nsmod PMSDIMDriverMod.ko
```

#### Loading the driver
To load the driver module without the use of the script use the following command:
```
sudo rmmod PMSDIMDriverMod.ko
```

### With the bash script
#### Loading the driver
To load the driver module using the provided script use the following command:
```
sudo sh PMSDIMDriverRun.sh 1 0
```
To enable *tail* output set the second parameter to '1'
```
sudo sh PMSDIMDriverRun.sh 1 1
```

#### Unloading the driver
To unload the driver module using the provided script use the following command:
```
sudo sh PMSDIMDriverRun.sh 2 0
```
To enable *tail* output set the second parameter to '1'
```
sudo sh PMSDIMDriverRun.sh 2 1
```

#### Script input options
The list of possible input/parameter combinations for the script are as follows:
```
sudo sh PMSDIMDriverRun.sh x y
```
* Parameter 1 (x):
   * 0 : dmesg
   * 1 : Load module
   * 2 : Unload module
   * 3 : Load and unload moule
* Parameter 2 (y):
  * 0 : desable tail
  * 1 : enable tail

The above list can be obtained by running the following command:
```
sudo sh PMSDIMDriverRun.sh
```
