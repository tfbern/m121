# Fachartikel
- [Fachartikel als Markdown](out/fachartikel.md)
- [Fachartikel als HTML](http://htmlpreview.github.io/?https://github.com/tfbern/m121/blob/master/.article/out/fachartikel.md.html)
- [Fachartikel als PDF](out/fachartikel.docx)
- [Fachartikel als PDF](out/fachartikel.pdf)

# Erstellung
## Schreiben
1. Text schreiben in Pandoc Markdown Format: *fachartikel.md*
2. Quellen im BibTeX Format erfassen in: *quellen.bib*

## Konvertieren
1. GFM Markdown Version erstellen: `.\Convert-Document -outFormat gfm`
2. HTML Version erstellen: `.\Convert-Document -outFormat html`
3. Word Version erstellen: `.\Convert-Document -outFormat docx`
4. PDF Version erstellen: `.\Convert-Document -outFormat pdf`
