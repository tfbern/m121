pandoc --biblatex -t latex -o body.tex body.md
latexmk -pdf fachartikel.tex
latexmk -c