
Debian
====================
This directory contains files used to package sberd/sber-qt
for Debian-based Linux systems. If you compile sberd/sber-qt yourself, there are some useful files here.

## sber: URI support ##


sber-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install sber-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sber-qt binary to `/usr/bin`
and the `../../share/pixmaps/sber128.png` to `/usr/share/pixmaps`

sber-qt.protocol (KDE)

