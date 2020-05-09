# Hacking caminhad

caminhad uses the meson build system. To compile it run the following in the
root directory of the repository:

```
meson build/
ninja -C build/
```

Meson uses out of tree builds, the `build` directory is just a recomendation.
You might want to use it because the repository contains a symlink pointing to
`build/compile_commands.json` to ease integration with Language Server
Protocol clients.

