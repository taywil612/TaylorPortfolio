This project’s main goal is to implement robot localization with the HMM algorithm. The robot performs two actions, sensing and moving. Multiple elements are 
implemented for this to be possible, including transitional probability, evidence conditional probability, filtering, and prediction.  

Transitional probabilities are calculated through the prediction function, where all possible actions (north,west,south,east) are initialized and are connected 
with the probability of the robot not moving. For moving westward, PW(St+1=B|St=A) = 0.10, and for moving northward PN(St+1=B|St=A) = 0.80.  
The evidence conditional probability is generated with the filtering function, with  P(Zt,w,n,e,s|St).
