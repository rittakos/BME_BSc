public class FlappyAgentSkeleton {
    static class StateDTO {
        public int birdPos;
        public int birdSpeed;
        public int tubeDistance;
        public int tubeHeight;

        public StateDTO(int birdPos, int birdSpeed, int tubeDistance, int tubeHeight) {
            this.birdPos = birdPos;
            this.birdSpeed = birdSpeed;
            this.tubeDistance = tubeDistance;
            this.tubeHeight = tubeHeight;
        }

        @Override
        public String toString() {
            return "StateDTO{" +
                    "birdPos=" + birdPos +
                    ", birdSpeed=" + birdSpeed +
                    ", tubeDistance=" + tubeDistance +
                    ", tubeHeight=" + tubeHeight +
                    '}';
        }
    }
    static class QTable implements java.io.Serializable {
        public double[][][][][] table;

        public QTable() {

        }

        public QTable(int[] stateSpaceSize, int actionDimension) {
            table = new double[stateSpaceSize[0]][stateSpaceSize[1]][stateSpaceSize[2]][stateSpaceSize[3]][actionDimension];
        }

        public double[] getActions(FlappyAgent.StateDTO state) {
            return table[state.birdPos][state.birdSpeed][state.tubeDistance][state.tubeHeight];
        }

        public FlappyAgent.QTable copy() {
            FlappyAgent.QTable res = new FlappyAgent.QTable();
            res.table = this.table.clone();
            return res;
        }
    }

    QTable qTable;
    int[] actionSpace;
    int nIterations;

    boolean test = false;

    public FlappyAgentSkeleton(int[] observationSpaceSize, int[] actionSpace, int nIterations) {
        this.qTable = new QTable(observationSpaceSize,actionSpace.length);
        this.actionSpace = actionSpace;
        this.nIterations = nIterations;
    }
    public int step(StateDTO state) {
        int action = 0;//

		for(int i = 0; i < qTable.getActions(state).length; ++i)
		{
			if(qTable.getActions(newState)[i] > action)
				action = qTable.getActions(newState)[i];
		}

        return action;
    }
    public void epochEnd(int epochRewardSum) {

    }
    public void learn(StateDTO oldState, int action, StateDTO newState, int reward) 
	{
		
		double x = qTable.getActions(oldState)[action];
		
		double max = 0;
		
		for(int i = 0; i < qTable.getActions(newState).length; ++i)
		{
			if(qTable.getActions(newState)[i] > max)
				max = qTable.getActions(newState)[i];
		}
		
		qTable.getActions(oldState)[action] += 0.5 *(reward + 0.7 * max - x);
    }
    public void trainEnd() {
        /*...*/

        //qTable = null;//
        test = true;
    }
}
