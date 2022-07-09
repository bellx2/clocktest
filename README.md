# Clock ms Test

時刻のmsの取得のための、[gettimeofday()](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/gettimeofday.2.html)、[clock_gettime](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/clock_getres.2.html)+ clx::date_timeの組み合わせのテストコード

gettimeofdayは非推奨で、clock_gettimeを使った方が良いとの事なので、両方併記。

```
*** gettimeofday() ***
seconds since epoch: 1657329847
milliseconds since epoch: 1657329847082
tv_usec (Microseconds): 82968
tv_usec (ms): 82

*** clock_gettime() ***
seconds since epoch: 1657329847
tv_usec (Nanoseconds): 83046708
tv_usec (ms): 83

*** to clx::date_time ***
2022-07-09T01:24:07.083
2022-07-09T01:24:07
```

## build
```
mkdir build
cd build; cmake ..
make
```

## note

clx::date_timeはエポック秒で処理されるため、msを使うにはgettimeofday()もしくはclock_gettime()を使う必要がある。取得した秒をclx::date_timeのコンストラクタに渡して正常に動作するかのテスト。

## 参考

https://linuxjm.osdn.jp/html/LDP_man-pages/man2/gettimeofday.2.html

https://linuxjm.osdn.jp/html/LDP_man-pages/man2/clock_getres.2.html
