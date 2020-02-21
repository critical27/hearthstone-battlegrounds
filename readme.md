## Hearthstone Battlegrounds
A simulator for hearthstone battlegrounds, inspired by [hearthstone-battlegrounds-simulator](https://github.com/twanvl/hearthstone-battlegrounds-simulator), more like a version rewritten. Thanks for its great work! It really help.

The reason to rewrite is that I think it is a little bit hard to test. Also a good opportunity to practise.

### build
Depends on glog, gtest and hsdata.
```
git submodule update --init --recursive
```

Then cmake it.

### todo
* Some trigger details need to be confirmed.
* Board parser. The only way to simulate is do it in unit test for now.
* And most importantly, Bob's tavern action (which include battlecry)
