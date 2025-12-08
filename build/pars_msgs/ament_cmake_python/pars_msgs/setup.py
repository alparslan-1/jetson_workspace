from setuptools import find_packages
from setuptools import setup

setup(
    name='pars_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('pars_msgs', 'pars_msgs.*')),
)
