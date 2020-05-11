pandoc --biblatex content.md -t latex -o content.tex
latexmk fachartikel.tex -pdf
latexmk -c
