#!/bin/bash

DRIV_NAME=PMSDIMDriverMod.ko
KERN_LOG=/var/log/kern.log

if [ $# -ge 1 ]; then
    if [ $1 -eq 0 ]; then
        echo "Log dump:"
        dmesg
        exit
    fi
fi

if [ $# -le 1 ]; then
    echo "Provide execution mode"
    echo "Parameter 1:"
    echo "  > 0 : dmesg"
    echo "  > 1 : Load module"
    echo "  > 2 : Unload module"
    echo "  > 3 : Load and unload moule"
    echo "Parameter 2:"
    echo "  > 0 : desable tail"
    echo "  > 1 : enable tail"
elif [ $1 -eq 1 ]; then
    insmod $DRIV_NAME
    if [ $? -eq 0 ]; then
        echo "Module loaded"
    else
        if [ $2 -eq 1 ]; then
            tail $KERN_LOG
        fi
        echo "FAIL"
        exit
    fi
    if [ $2 -eq 1 ]; then
        tail $KERN_LOG
    fi
elif [ $1 -eq 2 ]; then
    rmmod $DRIV_NAME
    if [ $? -eq 0 ]; then
        echo "Module unloaded"
    else
        if [ $2 -eq 1 ]; then
            tail $KERN_LOG
        fi
        echo "FAIL"
        exit
    fi
    if [ $2 -eq 1 ]; then
        tail $KERN_LOG
    fi
elif [ $1 -eq 3 ]; then
    insmod $DRIV_NAME
    if [ $? -eq 0 ]; then
        echo "Module loaded"
    else
        if [ $2 -eq 1 ]; then
            tail $KERN_LOG
        fi
        echo "FAIL"
        exit
    fi

    rmmod $DRIV_NAME
    if [ $? -eq 0 ]; then
        echo "Module unloaded"
    else
        if [ $2 -eq 1 ]; then
            tail $KERN_LOG
        fi
        echo "FAIL"
        exit
    fi
    if [ $2 -eq 1 ]; then
        tail $KERN_LOG
    fi
else
    echo "Invalid mode!"
    echo "Provide execution mode"
    echo "Parameter 1:"
    echo "  > 0 : dmesg"
    echo "  > 1 : Load module"
    echo "  > 2 : Unload module"
    echo "  > 3 : Load and unload moule"
    echo "Parameter 2:"
    echo "  > 0 : desable tail"
    echo "  > 1 : enable tail"
fi
