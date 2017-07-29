mdio-tool
=========
This is tool to read and write MII registers from ethernet physicals under linux.
It has been tested with Realtek and Marvell PHY's connected via PCIe and should work
with all drivers implementing the mdio ioctls.

mdio-tool comes with ABSOLUTELY NO WARRANTY; Use with care!

Syntax:
	mdio-tool [r/w] [devname] [addr] <value>
	./mdio-tool w eth0 0x10 0x0
	./mdio-tool r eth0 0x0


