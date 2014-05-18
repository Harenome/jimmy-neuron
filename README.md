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
