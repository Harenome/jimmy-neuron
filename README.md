Jimmy Neuron
============

[![Build Status](https://travis-ci.org/remove/jimmy-neuron.svg?branch=master)](https://travis-ci.org/remove/jimmy-neuron)

Projet d'Intelligence Artificielle, L3S6 Informatique, Université de Strasbourg.
Il s'agit d'implémenter un petit réseau de neurones.

Pré-requis
----------

### Fedora 20
#### Minimum
```bash
$ yum groupinstall "Development Tools"
$ yum install g++ man-pages gnuplot
```

#### Tests
```bash
$ yum install cxxtest cxxtest-doc
```

### Ubuntu
#### Minimum
```bash
$ apt-get update
$ apt-get install build-essential gnuplot
```

#### Tests
##### Ubuntu 12.04
```bash
$ add-apt-repository -y ppa:dhart/ppa
$ apt-get update
$ apt-get install cxxtest
$ cd /usr/bin && ln -s cxxtestgen.py cxxtestgen
```

##### Ubuntu >= 12.10
```bash
$ apt-get update
$ apt-get install cxxtest
```

Compilation
-----------
```bash
$ make
```

Lancement
---------
### Lancement du programme
```bash
$ bin/jimmy-neuron [--option=valeur | --option=valeurs,avec,virgules]
```

### Options
- ```--help``` : Afficher une aide.
- ```--version``` : Afficher la version.
- ```--colony-size=N``` : Fixer la taille maximale de la colonie à N.
- ```--max-generations=N``` : Fixer le nombre maximal de générations (pour éviter
  de boucler _ad vitam æternam_) à N..
- ```--probabilities=N,O,P``` : Changer les probabilités de cross-over, mutation
  et clonage; dans cet ordre. Les valeurs doivent être séparées par des virgules.
  La somme des probabilités doit être égale à 100.
- ```--weight-range=N``` : Changer la fourchette des poids.
- ```--temp-file=path``` : Changer le chemin à utiliser pour le fichier temporaire.

#### Exemples
```bash
$ bin/jimmy-neuron --colony-size=5
$ bin/jimmy-neuron --max-generations=3000
$ bin/jimmy-neuron --probabilities=15,15,70
$ bin/jimmy-neuron --colony-size=10 --weight-range=1.5 --max-generations=3000
```

Builds
------

### Remove
- ```master```: [![Build Status](https://travis-ci.org/remove/jimmy-neuron.svg?branch=master)](https://travis-ci.org/remove/jimmy-neuron)
- ```dev```: [![Build Status](https://travis-ci.org/remove/jimmy-neuron.svg?branch=dev)](https://travis-ci.org/remove/jimmy-neuron)

### Harenome
- ```master```: [![Build Status](https://travis-ci.org/Harenome/jimmy-neuron.svg?branch=master)](https://travis-ci.org/Harenome/jimmy-neuron)
- ```dev```: [![Build Status](https://travis-ci.org/Harenome/jimmy-neuron.svg?branch=dev)](https://travis-ci.org/Harenome/jimmy-neuron)

License
-------
Copyright © 2014 Harenome RAZANAJATO, Jérémy MEYER

Ce projet est libre. Vous pouvez le redistribuer ou le modifier selon les termes
de la license « Do What The Fuck You Want To Public License », Version 2, comme
publiée par Sam Hocevar. Pour de plus amples informations, veuillez vous référer
au fichier COPYING, ou bien http://www.wtfpl.net/.
