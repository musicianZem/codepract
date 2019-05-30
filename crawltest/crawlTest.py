from urllib.request import urlopen
from bs4 import BeautifulSoup

html = urlopen("http://www.ff14.inven.com")
bsObject = BeautifulSoup(html, "html.parser")

print(bsObject.head.title)






