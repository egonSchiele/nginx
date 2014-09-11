# Nginx

My fork of nginx for playing around in.

To build with the lua module, first export these env vars:

    export LUA_LIB=/usr/local/lib
    export LUA_INC=/usr/local/include

Then:

    ./configure --add-module=/Users/adit/nginx/src/misc/lua-nginx-module --add-module=/Users/adit/nginx/src/misc/ngx_devel_kit
    make
    sudo make install

## Writing your own nginx module

I modified the built-in google perftools module to make my own module instead. It works. Simple usage: in nginx, add 'adit watterson;' as a top-level directive (you can use any string in place of watterson). Now start the server and look at the log. You should see some messages printed out, including messages that reference your string (watterson or whatever you put).

## Useful links

- [ngx_devel_kit - an Nginx module that adds additional generic tools that module developers can use in their own modules](https://github.com/simpl/ngx_devel_kit)
- [ngx_lua - embed lua inside nginx](https://github.com/openresty/lua-nginx-module)
