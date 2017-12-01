# Broadcast Using This Tool

butt (broadcast using this tool) is an easy to use, multi OS streaming tool. It supports ShoutCast and IceCast and runs on Linux, MacOS and Windows. The main purpose of butt is to stream live audio data from your computers Mic or Line input to an Shoutcast or Icecast server. Recording is also possible. It is NOT intended to be a server by itself or automatically stream a set of audio files.

## This Repository

This repository has been created out of the need to have butt read audio input from other channels than the first two of an audio device.

## Compiling

Theoretically it should compile the same way as before; install dependencies, hit `./configure && make` and you should be all set.

However, for me those instructions didn’t work on macOS Sierra. Here is how I did make it work (together with a couple of fixes that are in the repository):

```
$ CPPFLAGS="-ObjC++ -I../xcode/include" ./configure
$ make
```

I have no idea how to fix the underlying issues because frankly, I despise C or C++ or whatever unholy mongrel of a language this tool is written in.

## Closing Remarks

Anyway, this works for me. It doesn’t seem to crash, the choices I make are persisted, and my world has gotten a little bit better because of this.

Big thanks to Daniel Nöthen for creating butt in the first place; without him I’d have nothing to patch.
