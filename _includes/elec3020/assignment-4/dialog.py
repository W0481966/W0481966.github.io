#!/usr/bin/env python3

import locale
from dialog import Dialog

locale.setlocale(locale.LC_ALL, '')

d = Dialog(dialog='dialog')
d.set_background_title('Insult Chris, that Craven Curmudgeon')

choices = [
        ('Ninny', 'Absolutely execrable', False),
        ('Nitwit', 'The vilest of the vile', False),
        ('Nincompoop', 'Awful, atrocious and abhorrent', False),
        ('Numpty', 'Dreadful, dastardly and deviant', False),
        ('Nogoodnik', 'A scummy scoundrel', False),
        ('Neer-do-well', 'Putrid, repugnant and nauseating', False)
]

while True:
    code, tag = d.radiolist('What best describes Chris?', choices=choices)

    if code == Dialog.OK and tag:
        d.msgbox('Agreed', title=f'What a {tag}!')
        break
    else:
        d.msgbox('Don\'t be shy, pick one!', title='Now, now!')
