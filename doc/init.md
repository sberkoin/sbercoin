Sample init scripts and service configuration for sberd
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/sberd.service:    systemd service unit configuration
    contrib/init/sberd.openrc:     OpenRC compatible SysV style init script
    contrib/init/sberd.openrcconf: OpenRC conf.d file
    contrib/init/sberd.conf:       Upstart service configuration file
    contrib/init/sberd.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "sber" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes sberd will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, sberd requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, sberd will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that sberd and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If sberd is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running sberd without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/sber.conf.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/sberd
Configuration file:  /etc/sber/sber.conf
Data directory:      /var/lib/sberd
PID file:            `/var/run/sberd/sberd.pid` (OpenRC and Upstart) or `/run/sberd/sberd.pid` (systemd)
Lock file:           `/var/lock/subsys/sberd` (CentOS)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the sber user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
sber user and group.  Access to sber-cli and other sberd rpc clients
can then be controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the sber group
access to files under it _if_ the files themselves give permission to the
sber group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/sber/sber.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/sber/sber.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `BITCOIND_DATADIR` for
OpenRC).

### macOS

Binary:              `/usr/local/bin/sberd`
Configuration file:  `~/Library/Application Support/SBER/sber.conf`
Data directory:      `~/Library/Application Support/SBER`
Lock file:           `~/Library/Application Support/SBER/.lock`

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start sberd` and to enable for system startup run
`systemctl enable sberd`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename sberd.openrc to sberd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/sberd start` and configure it to run on startup with
`rc-update add sberd`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop sberd.conf in /etc/init.  Test by running `service sberd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy sberd.init to /etc/init.d/sberd. Test by running `service sberd start`.

Using this script, you can adjust the path and flags to the sberd program by
setting the SBERD and FLAGS environment variables in the file
/etc/sysconfig/sberd. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.sber.sberd.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.sber.sberd.plist`.

This Launch Agent will cause sberd to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run sberd as the current user.
You will need to modify org.sber.sberd.plist if you intend to use it as a
Launch Daemon with a dedicated sber user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
