

/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o main.o PostBot.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -c -o bank2.o bank2.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o bank3.o bank3.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wl-yt0x01 -Wl-yo4 -o PostBot.gb main.o bank2.o bank3.o

cp PostBot.gb /www/cloudboy/htdocs/roms/postbank.gb
