# Fachartikel
## Dokumente

- [Fachartikel als Markdown](out/fachartikel.commonmark.md)
- [Fachartikel als HTML](http://htmlpreview.github.io/?https://github.com/tfbern/m121/blob/master/.article/out/fachartikel.html)
- [Fachartikel als Word](out/fachartikel.docx)
- [Fachartikel als PDF](out/fachartikel.pdf)

## Erstellung
### Schreiben

1. Text schreiben in Pandoc Markdown Format: *fachartikel.md*
2. Quellen im BibTeX Format erfassen in: *quellen.bib*

### Konvertieren
Auf dem System muss *pandoc* installiert sein. Für die Erstellung von PDFs muss zusätzlich *latexmk* und *pdfmake* installiert sein, 
sprich am besten ein ganzes LaTeX System wie Tex Live.

1. CommonMark Markdown Version erstellen: `.\Convert-Document fachartikel.md`
2. HTML Version erstellen: `.\Convert-Document fachartikel.md html`
3. LaTex Version erstellen: `.\Convert-Document fachartikel.md latex`
4. Word Version erstellen: `.\Convert-Document fachartikel.md docx`
5. PDF Version erstellen: `.\Convert-Document fachartikel.md pdf`

# Links

- [CommonMark](https://commonmark.org)
- [GitHub Flavored Markdown Spec](https://github.github.com/gfm/#link-reference-definitions)
- [Pandoc a universal document converter](https://pandoc.org/)
  - [Pandoc Manual](https://pandoc.org/MANUAL.html#)
- [Citation Style Language](https://citationstyles.org)
- [BibTeX](https://de.wikipedia.org/wiki/BibTeX)
- [Latexmk](https://mg.readthedocs.io/latexmk.html)
