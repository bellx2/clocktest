# Clock ms Test

時刻のmsの取得のための、gettimeofday() + clx::date_timeの組み合わせのテスト

```
seconds since epoch: 1657327337
milliseconds since epoch: 1657327337012
tv_usec (Microseconds): 12896
tv_usec (ms): 12
2022-07-09T00:42:17.012
2022-07-09T00:42:17
```

## build
```
mkdir build
cd build; cmake ..
make
```

## note

clx::date_timeはエポック秒で処理されるため、msを使うにはgettimeofday()を使う必要がある。gettimeofday()で取得したtimeval型をclx::date_timeのコンストラクタに渡して正常に動作するかのテスト。

