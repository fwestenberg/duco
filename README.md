Dit is een incomplete, niet volledige werkende Duco implementatie voor ESPHome. 
Zorg voor de volgende mapstructuur:

esphome 
..components
....duco

Plaats deze bestanden in de duco map, samen met deze bestanden van Arne Mauer:

- CC1101.cpp
- CC1101.h
- DucoCC1101.cpp
- DucoCC1101.h
- DucoPacket.h

Flash de ESP met de bestanden en voer de join service uit. In het ESPHome log komt nu een network ID voorbij, plak deze in duco_fan.cpp op deze regel:
->  int id[4] = {0x00, 0x02, 0x4e, 0x26};

Als het goed is, heb je nu communicatie met je Duco box gemaakt en kan je commando's versturen.
