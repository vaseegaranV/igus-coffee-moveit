from setuptools import find_packages
from setuptools import setup

setup(
    name='igus_rebel_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('igus_rebel_msgs', 'igus_rebel_msgs.*')),
)
