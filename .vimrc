" Allen's VIM configuration
" Dedicated to Competitive Programming

"import pathogen package manager
execute pathogen#infect()

"style
syntax enable
set background=light
"colorscheme solarized

"template path for F4
"template name: .cpp/.python/.rust etc
let s:tmp_path="~/.vim/templates/"

set ts=2
set sw=2
set sts=2
set ai
set fdm=marker

" Supported type list
" It's the user's responsibility to keep these command properly formatted
"how item presented:
"          filetype : [ compile command, compile flags    , execution command, [searching-term, additional-optional-flag] ]
let s:stp = { 
						 \"cpp" : ['!clang++-3.8 ' , '-o %< -DALNDBG ', '! ./%<',
																													\["math\.h", " -lm "], ["--USE C++11", " -std=c++11 "], ["--USE O2", " -O2 "]],
             \"rust": ['!rustc '       ,       ''         , '! ./%<',],
					 \"python": ['!echo '        ,       ' need not compile', '!python %'],
\}

"auto compiling
func! DoCompile()
	exec "w"
	
	let compCmd=s:stp[&filetype]
	let compilecmd=compCmd[0]
	let compileflag=compCmd[1]
	if len(compCmd) > 3
		let tmp = compCmd
		for i in range(3, len(tmp) - 1)
			if search(tmp[i][0]) != 0
				let compileflag .= tmp[i][1]
			endif
		endfor
	endif

	exec compilecmd ." % ".compileflag
endfunc

func! CompileCode()
	exec "call DoCompile()"
endfunc

"auto run
func! RunResult()
	exec "w"
	if has_key(s:stp, &filetype) == 0
		echo "Error: Unsupported filetype ".&filetype.", saved"
		return
	endif
	exec "call CompileCode()"
	exec s:stp[&filetype][2]
endf

func! InsertTemplate()
	execute "0read" . s:tmp_path . "." . &filetype
	call SetupCursor()
endfunc

func! SetupCursor()
	let q=searchpos("")
	if q[1] != 0 || q[2] != 0
		execute "normal! 12x"
		execute "normal! i"
	endif
endfunc

map <F4> :call InsertTemplate()<CR>
map <F5> :call CompileCode()<CR>
map <F6> :call RunResult()<CR>
