# test_sn_dohki 社畜のキーボード「新入社員の同期」

![test_sn_dohki](https://i.imgur.com/jFG8ZiQ.jpeg)  
http://www.neko.ne.jp/~freewing/hardware/usb_diy_keyboard_dohki/  
「新入社員の同期」で使える QMKのソース。  
※ 本プログラムは「遊舎工房」等とは一切関係が無い非公式のもので、FREE WINGが独自に作成した物となります。  

*A short description of the keyboard/project*

* Keyboard Maintainer: [Y.Sakamoto](https://github.com/FREEWING-JP)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make test_sn_dohki:default

Flashing example for this keyboard:

    make test_sn_dohki:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
