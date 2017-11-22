TD="/home/savchenk/work/osa11/software/ii_context/ii_context"
cd $TD

export PFILES=$TD:$PFILES
./ii_context \
    idxLowThre="$REP_BASE_PROD/scw/1857/rev.001/idx/isgri_context_index.fits[1]" \
    idxNoisy="$REP_BASE_PROD/scw/1857/rev.001/idx/isgri_prp_noise_index.fits[1]" \
    revolution=1857
