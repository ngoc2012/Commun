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

* `Ctrl+W` `+/-`:   increase/decrease height (ex. `20<C-w>+`)
* `Ctrl+W` `>/<`:   increase/decrease width (ex. `30<C-w><`)
* `Ctrl+W` `_`:     set height (ex. `50<C-w>_`)
* `Ctrl+W` `|`:     set width (ex. `50<C-w>|`)
* `Ctrl+W` `=`:     equalize width and height of all windows

* `:resize 60`
* `:res +3.5`
* `:res 4`
* `:vertical resize 80`


## Files
### Copy a part of document to a file
* `:100,200w filename`:                 copy lines 100 to 200 to file
* Select with `V` -> `:'<,'>w > fn`:    copy to file 
* Select with `V` -> `:'<,'>w >> fn`:   append 

## Macros
* `q<register><commands>q`: new macro
* `@<register>`:            apply macro
* `:reg h`:                 review macro
* `:'<,'>norm@a`:           apply macro in multiple lines

## Indentation
Use :set cindent (:set cin for short) or :set smartindent (:set si for short). If your line ends in an opening brace, and you hit Enter, the following line will automatically be indented one additional level. (This is better than :set autoindent, which merely indents the next line at the same level.) cindent is better tailored to C-like languages, while smartindent is more versatile for use with other programming languages.

## Visual block 'V'

[Demo](https://www.youtube.com/watch?v=Ydzw70SvF-g&t=193s)

* "I" to insert to the left
* "A" to append to the right
* "c" to change the Visual Block 
* "d" to delete the Visual Block
* "o" to go to the opposite corner
