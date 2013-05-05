$modelname	"props\banana.mdl"
$cdmaterials	"models\props\"
$scale 3

$body mybody	"banana.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"banana.smd"

$collisionmodel	"banana.smd" { $concave }