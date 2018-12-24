wget https://upload.wikimedia.org/wikipedia/commons/a/a2/Cat_Golden_Chinchilla.jpg -O cat.jpg
wget https://upload.wikimedia.org/wikipedia/commons/2/2d/Cane_corso_g%C5%82owa_profil_493o.jpg -O dog.jpg
python3 ./attack_weixin_downsample.py cat.jpg dog.jpg
