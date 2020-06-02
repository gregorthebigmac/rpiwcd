# rpiwcd - Raspberry Pi Watchdog Client Daemon

This is the client version of the Raspberry Pi Watchdog program. Here is the short and skinny of how this works, as well as terminology:

## Server

The "server" in this case is the Raspberry Pi, while the "clients" in this case are any devices on the network which rely on this for knowing if the power's out.

The Raspberry Pi is serving as a "canary in the coal mine" for the power to your mains. The Raspberry Pi should *not* be plugged into any UPS or battery backup, while the clients *are* on a UPS.

## Scenarios

Under normal operation, the Raspberry Pi does almost nothing. It occupies one port on a network switch, and clients periodically ping the Raspberry Pi to see if it's still up. The IP for the Raspberry Pi is stored in the client's config file. If the Raspberry Pi returns a ping, that means there is power to the mains, and the server is *not* running on battery power. If the Raspberry Pi does *not* return a ping, that means the power is out, and the client needs to react.

### Power Goes Out

When the power goes out, the Raspberry Pi loses power, and stops communicating with the clients. When this happens, the clients will gracefully shutdown immediately. There is a *bit* more to it than that, however. What if the Raspberry Pi was simply bogged down for whatever reason, and didn't return a ping? The clients will account for this.

If a client pings the Raspberry Pi, and a ping is not returned, it will go into "aggressive ping mode," and begin pinging the Raspberry Pi more frequently for a designated period of time (all of this is determined by config files which the user may change at will), and when the client is satisfied that the Raspberry Pi has gone down due to lack of power, the client will shut itself down.

### Power is Restored

When the power is restored, the Raspberry Pi comes back online, and the server daemon starts up upon boot via cron job. When it begins running, it looks for clients in its config file, and begins pinging them. If no ping is returned, it sends a WoL packet to the client, and waits a designated amount of time (also set in config file) before pinging it. If no ping is returned, it sends another WoL packet. If a ping *is* returned, it stops pinging the client, and stops sending WoL packets to it. It does this for every client in the config file.
