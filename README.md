
# 🌦️ WeatherLinkSystem 🌐

Bienvenue dans l'univers captivant de WeatherLinkSystem, un projet météorologique élaboré avec passion par des étudiants. WeatherLinkSystem se distingue en tant que système météorologique intégré, alliant un site web interactif, une Raspberry Pi en tant que serveur central et une station météo. Suivez notre projet !

## 🏫 À Propos de l'INSSET Saint-Quentin

L'INSSET (Institut Supérieur des Sciences, de l'Enseignement et de la Technologie) Saint-Quentin est un institut située dans la charmante ville de Saint-Quentin, en France. Affiliée à l'Université de Picardie Jules Verne, l'INSSET propose des formations dans des domaines variés, allant de la mécanique à l'informatique en passant par le génie électrique.
[![Logo](https://i.ibb.co/58wMW5K/INSSET-logo-RVB.png)](http://www.insset.u-picardie.fr/)
## 🚀 Objectif du Projet

Notre mission ? Concevoir une station météo intelligente et accessible à tous, combinant un site web interactif, une Raspberry Pi en tant que chef d'orchestre, et une station météo  pleine de capteurs.

## 🌐 Ce qui vous attend

- **Site Web Intéractif :** Explorez des données météorologiques en temps réel et interagissez avec notre site convivial.
- **Raspberry Pi Serveur :** Découvrez les capacités d'une Raspberry Pi qui coordonne toutes les opérations et offre des fonctionnalités avancées.
- **Station Météo  :** Plongez dans le monde de la programmation  en utilisant notre station météo équipée de capteurs pour mesurer divers paramètres.



## 👥 Contributeurs

- [@LordYoni](https://github.com/LordYoni)
- [@GrosChien](https://github.com/GrosChien) (Eliot)
- Mr. Pierens Xavier (superviseur du projet)
## 📃 Documentation
Vous pourez retrouvez la courte documentation du projet ici :
[Documentation](https://github.com/LordYoni/WeatherLinkSystem/tree/main/documentation)


## 🛠️ Installation Raspberry


Mettre à jour le système :
```bash
  sudo apt update
  sudo apt upgrade
  sudo apt update
```
Installez Apache2 :
```bash
  sudo apt install apache2
```

Vous assurez-vous que l'utilisateur "admin" possède les droits sur le dossier HTML :
```bash
  sudo chown -R admin /var/www/html
```
Installez MariaDB Server :
```bash
  sudo apt install mariadb-server
```

Installez PHP et PHPMyAdmin :
```bash
  sudo apt install php
  sudo apt install phpmyadmin
```
Lors de l'installation de phpmyadmin, choisissez "apache2" et appuyez sur "yes".
Créez un mot de passe pour phpmyadmin.


Configurez l'accès à MySQL :
```bash
  sudo mysql -u root -p
```
Entrez le mot de passe root MySQL :
```bash
  GRANT ALL PRIVILEGES ON *.* TO 'adminSQL'@'localhost' IDENTIFIED BY 'StationSQL' WITH   GRANT OPTION;
```

Ajoutez la configuration pour PHPMyAdmin à Apache :
```bash
  sudo nano /etc/apache2/apache2.conf
```
Ajoutez la ligne suivante tout en bas du fichier :
```bash
  Include /etc/phpmyadmin/apache.conf
```
Quittez et sauvegardez

Redémarrez le service Apache :
```bash
  sudo service apache2 restart
```

Installez Python3 et pip :
```bash
  sudo apt-get install python3-pip
```

Configurez un environnement virtuel Python :
```bash
  python3 -m venv /home/venv
  source /home/venv/bin/activate
```

Installez les bibliothèques Python nécessaires :
```bash
  pip install pyserial
  pip install mysql-connector-python
```



## 🔗 Annexe

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

## 📬 Contact

Pour toute question, suggestion, ou simplement pour discuter de météo, n'hésitez pas à nous contacter à taine.yoni@gmail.com

Restez connectés, car WeatherLinkSystem prend forme ! 🌈🛰️⚙️

## 📝 Licence

Ce projet est sous licence MIT, ce qui signifie que vous avez la liberté de l'utiliser et de le modifier selon vos besoins. Consultez le fichier [LICENSE](https://github.com/LordYoni/WeatherLinkSystem/blob/main/LICENSE) pour plus d'informations.
