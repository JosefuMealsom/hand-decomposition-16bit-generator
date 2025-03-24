#!/bin/bash

ffmpeg -framerate 1 -i ./tex_hand_silhouette.raw_%d.jpg -r 30 output.mp4
