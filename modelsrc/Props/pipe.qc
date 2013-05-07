$modelname	"props\pipe.mdl"
$cdmaterials	"models\props\"
$scale 28

$body mybody	"pipe.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"pipe.smd"

$collisionmodel	"pipe.smd" { $concave }