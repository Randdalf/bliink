$modelname	"props\crate.mdl"
$cdmaterials	"models\props\"
$scale 24

$body mybody	"crate.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"crate.smd"

$collisionmodel	"crate.smd" { $concave }