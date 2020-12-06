Ajit's Build Docker Image
=========================
Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

This folder contains Dockerfile to create
the build image with the whole ajit build and
the temporary files with sources.
(The size of this image can be huge >5GB)

The image is self-sufficient,
i.e. no local store or volume is used
to save persistent data.
One can mount a volume to save persisten data if needed.
