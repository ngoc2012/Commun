# Vim

## Commands
* `:!`:     Terminal command
* `:term`:  Viewport with terminal

## Edition
* `:%s/.$//`: Delete last characters of lines

### Replace in multiple files
* `:args *.c`: Select files
* `:argdo! %s/\s\+$//e | update`: Replace in files

## Views
### Resize

* `Ctrl+W` `+/-`: increase/decrease height (ex. `20<C-w>+`)
* `Ctrl+W` `>/<`: increase/decrease width (ex. `30<C-w><`)
* `Ctrl+W` `_`: set height (ex. `50<C-w>_`)
* `Ctrl+W` `|`: set width (ex. `50<C-w>|`)
* `Ctrl+W` `=`: equalize width and height of all windows

* `:resize 60`
* `:res +3.5`
* `:res 4`
* `:vertical resize 80`


## Files
### Copy a part of document to a file
* `:100,200w filename`: copy lines 100 to 200 to file
* Select with `V` -> `:'<,'>w > fn`:    copy to file 
* Select with `V` -> `:'<,'>w >> fn`:   append 

## Macros

* `q<register><commands>q`: new macro
* `@<register>`: replay macro
* `:reg h`: review macro

