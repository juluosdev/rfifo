## Objectives
Create a ring fifo for accessing chunk buffer directly
so that don't need memory copy.

## How to build
```
make -C src
```

## run tests
```
make -C src tests
```

example file

```
./test_rfifo
1496153373.601203 thread producer started 47007882577664
1496153373.601351 thread consumer started 47007880476416
1496153373.601466 1 cnt=1 rc = 0, data: c0 data2
1496153373.649715 3 cnt=1 rc = 0, data: c1 data3
1496153373.682933 4 cnt=1 rc = 0, data: c2 data4
1496153373.716066 5 cnt=1 rc = 0, data: c3 data5
1496153373.749232 6 cnt=1 rc = 0, data: c4 data6
1496153373.782385 7 cnt=1 rc = 0, data: c5 data7
1496153373.815548 8 cnt=1 rc = 0, data: c0 data8
1496153373.848738 9 cnt=1 rc = 0, data: c1 data9
1496153373.881952 10 cnt=1 rc = 0, data: c2 data10
1496153373.915104 11 cnt=1 rc = 0, data: c3 data11
1496153373.948235 12 cnt=1 rc = 0, data: c4 data12
1496153373.981385 13 cnt=1 rc = 0, data: c5 data13
1496153374.014537 14 cnt=1 rc = 0, data: c0 data14
1496153374.047673 15 cnt=1 rc = 0, data: c1 data15
1496153374.080790 16 cnt=1 rc = 0, data: c2 data16
1496153374.113896 17 cnt=1 rc = 0, data: c3 data17
1496153374.147001 18 cnt=1 rc = 0, data: c4 data18
1496153374.180118 19 cnt=1 rc = 0, data: c5 data19
1496153374.213236 20 cnt=1 rc = 0, data: c0 data20
1496153374.246355 21 cnt=1 rc = 0, data: c1 data21
1496153374.279488 22 cnt=1 rc = 0, data: c2 data22
1496153374.312629 23 cnt=1 rc = 0, data: c3 data23
1496153374.345770 24 cnt=1 rc = 0, data: c4 data24
1496153374.378903 25 cnt=1 rc = 0, data: c5 data25
1496153374.412014 26 cnt=1 rc = 0, data: c0 data26
1496153374.445166 27 cnt=1 rc = 0, data: c1 data27
1496153374.478319 28 cnt=1 rc = 0, data: c2 data28
1496153374.511489 29 cnt=1 rc = 0, data: c3 data29
1496153374.544641 30 cnt=1 rc = 0, data: c4 data30
1496153374.577760 31 cnt=1 rc = 0, data: c5 data31
1496153374.610858 32 cnt=1 rc = 0, data: c0 data32
1496153374.643963 33 cnt=1 rc = 0, data: c1 data33
1496153374.677071 34 cnt=1 rc = 0, data: c2 data34
1496153374.710162 35 cnt=1 rc = 0, data: c3 data35
1496153374.743256 36 cnt=1 rc = 0, data: c4 data36
1496153374.776367 37 cnt=1 rc = 0, data: c5 data37
1496153374.809470 38 cnt=1 rc = 0, data: c0 data38
1496153374.842618 39 cnt=1 rc = 0, data: c1 data39
1496153374.875736 40 cnt=1 rc = 0, data: c2 data40
1496153374.908891 41 cnt=1 rc = 0, data: c3 data41
1496153374.942028 42 cnt=1 rc = 0, data: c4 data42
1496153374.975180 43 cnt=1 rc = 0, data: c5 data43
1496153375.008333 44 cnt=1 rc = 0, data: c0 data44
1496153375.041486 45 cnt=1 rc = 0, data: c1 data45
1496153375.074604 46 cnt=1 rc = 0, data: c2 data46
1496153375.107756 47 cnt=1 rc = 0, data: c3 data47
1496153375.140919 48 cnt=1 rc = 0, data: c4 data48
1496153375.174072 49 cnt=1 rc = 0, data: c5 data49
1496153375.207232 50 cnt=1 rc = 0, data: c0 data50
1496153375.240391 51 cnt=2 rc = 0, data: c1 data51
1496153375.273545 52 cnt=2 rc = 0, data: c2 data52
1496153375.306697 53 cnt=2 rc = 0, data: c3 data53
1496153375.339886 54 cnt=2 rc = 0, data: c4 data54
1496153375.373061 55 cnt=2 rc = 0, data: c5 data55
1496153375.406249 56 cnt=2 rc = 0, data: c0 data56
1496153375.439430 57 cnt=2 rc = 0, data: c1 data57
1496153375.472608 58 cnt=2 rc = 0, data: c2 data58
1496153375.505810 59 cnt=2 rc = 0, data: c3 data59
1496153375.538958 60 cnt=2 rc = 0, data: c4 data60
1496153375.572151 61 cnt=2 rc = 0, data: c5 data61
1496153375.605339 62 cnt=2 rc = 0, data: c0 data62
1496153375.638499 63 cnt=2 rc = 0, data: c1 data63
1496153375.671689 64 cnt=2 rc = 0, data: c2 data64
1496153375.704893 65 cnt=2 rc = 0, data: c3 data65
1496153375.738068 66 cnt=2 rc = 0, data: c4 data66
1496153375.771261 67 cnt=2 rc = 0, data: c5 data67
1496153375.804431 68 cnt=2 rc = 0, data: c0 data68
1496153375.837623 69 cnt=2 rc = 0, data: c1 data69
1496153375.870812 70 cnt=2 rc = 0, data: c2 data70
1496153375.903998 71 cnt=2 rc = 0, data: c3 data71
1496153375.937188 72 cnt=2 rc = 0, data: c4 data72
1496153375.970334 73 cnt=2 rc = 0, data: c5 data73
1496153376.003523 74 cnt=2 rc = 0, data: c0 data74
1496153376.036714 75 cnt=2 rc = 0, data: c1 data75
1496153376.069919 76 cnt=2 rc = 0, data: c2 data76
1496153376.103086 77 cnt=2 rc = 0, data: c3 data77
1496153376.136240 78 cnt=2 rc = 0, data: c4 data78
1496153376.169394 79 cnt=2 rc = 0, data: c5 data79
1496153376.202583 80 cnt=2 rc = 0, data: c0 data80
1496153376.235799 81 cnt=2 rc = 0, data: c1 data81
1496153376.268957 82 cnt=2 rc = 0, data: c2 data82
1496153376.302146 83 cnt=2 rc = 0, data: c3 data83
1496153376.335336 84 cnt=2 rc = 0, data: c4 data84
1496153376.368504 85 cnt=2 rc = 0, data: c5 data85
1496153376.401692 86 cnt=1 rc = 0, data: c0 data86
```
