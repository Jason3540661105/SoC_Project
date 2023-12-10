onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib uart_test1_opt

do {wave.do}

view wave
view structure
view signals

do {uart_test1.udo}

run -all

quit -force
