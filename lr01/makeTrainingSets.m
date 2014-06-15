function makeTrainingSets(featureType, featureInterval, labelType, labelInterval, labelVal)

% Using the given parameters (assuming feature sets and labels already exist),
% create complete training sets for all equities.
%
% Author: Marshall Farrier
% Since: 2014-04-14
% 

equities = { "cat", "dd", "f", "ge", "ibm", "jnj", "jpm", "xom" };
for i = 1:length(equities)
    makeClosesTrainingSetEq(equities{i}, featureType, featureInterval, labelType, labelInterval, labelVal);
endfor

end
