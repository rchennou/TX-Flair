:writefromstart
0,/%flair:license{/ {
    p           # print line
    $b exit     # exit if the license not found (branch to exit if on on the last line)
}

# put license file after the line with %flair:license{
/%flair:license{/ {
    r ./LICENSE-header.txt
}

:writetillend
/%flair:license}/,$ {
    p           # print line
}

:exit

