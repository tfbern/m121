# Fachartikel
- [Fachartikel als Markdown](fachartikel.md)
- [Fachartikel als HTML](fachartikel.html)
- [Fachartikel als PDF](fachartikel.pdf)

# Erstellung
1. Quellen erfassen in *quellen.bib*
2. Text schreiben in *body.md*
3. Body mit `pandoc` in LaTex konvertieren[^1]
4. Body wird eingebunden in das LaTex Template *fachartikel.tex*
4. PDF erstllen mit `latexmk`[^2]
5. Weitere Dokumente erstellen mit `pandoc`.[^3] Für Publikation auf GitHub und GitLab das Format *gfm* wählen.  
\
\

-------------  
[^1]: `pandoc --biblatex -t latex -o body.tex body.md`
[^2]: `latexmk -pdf fachartikel.tex`
[^3]: `pandoc -F pandoc-citeproc --csl din-1505-2-numeric.csl --toc -V toc-title:"Inhaltsverzeichnis" -s -t $_ -o formats/fachartikel.$_ fachartikel.tex`
