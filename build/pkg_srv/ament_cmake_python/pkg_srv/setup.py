from setuptools import find_packages
from setuptools import setup

setup(
    name='pkg_srv',
    version='0.0.0',
    packages=find_packages(
        include=('pkg_srv', 'pkg_srv.*')),
)
