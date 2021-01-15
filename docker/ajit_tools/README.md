Ajit's Tools Docker Image
=========================
Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

This docker image builds on top of `ajit_build` image,
by deleting most of the redundant stuff to make
the image light.

The image is self-sufficient,
i.e. no local store or volume is used
to save persistent data.
One can mount a volume to save persisten data if needed.
