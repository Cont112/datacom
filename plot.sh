#!/bin/bash
gnuplot -persist <<-EOFMarker
  plot [-2:100] [-4:4] "client.txt" with steps
EOFMarker
