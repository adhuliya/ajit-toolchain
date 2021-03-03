import difflib
with open('main.s') as f1:
    f1_text = f1.read()
with open('main.dis.s') as f2:
    f2_text = f2.read()
for line in difflib.unified_diff(f1_text, f2_text, fromfile='main.s', tofile='main.dis.s', lineterm=''):
    print line
