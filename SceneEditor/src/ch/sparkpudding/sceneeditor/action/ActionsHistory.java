package ch.sparkpudding.sceneeditor.action;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 16 avr. 2019
 * 
 *         This class is a singleton who handle the differents actions to allow
 *         basic undo and redo management
 * 
 */
public class ActionsHistory {

	private static ActionsHistory INSTANCE = new ActionsHistory();

	private List<HistoryEventListener> eventListeners;

	private int stackPointer = -1;
	private Stack<AbstractAction> actionsStack;

	private ActionsHistory() {
		this.actionsStack = new Stack<AbstractAction>();
		this.eventListeners = new ArrayList<HistoryEventListener>();
	}

	/**
	 * Insert an action in the history
	 * 
	 * @param action the action to add
	 */
	public void insertAction(AbstractAction action) {

		deleteElementsAfterPointer();
		actionsStack.push(action);

		stackPointer++;

		fireHistoryEvent();
	}

	/**
	 * Delete all the action after the pointer
	 */
	private void deleteElementsAfterPointer() {

		if (actionsStack.size() < 1)
			return;

		for (int i = actionsStack.size() - 1; i > stackPointer; i--) {
			actionsStack.remove(i);
		}

	}

	/**
	 * Undo the action at the pointer without deleting it to allow redo
	 */
	public void undo() {

		AbstractAction action = actionsStack.get(stackPointer);
		action.undoAction();

		stackPointer--;

		fireHistoryEvent();
	}

	/**
	 * Redo the last undoed action
	 */
	public void redo() {

		if (stackPointer == actionsStack.size() - 1)
			return;

		stackPointer++;

		AbstractAction action = actionsStack.get(stackPointer);
		action.doAction();

		fireHistoryEvent();
	}

	/**
	 * Add a listener for the event of the History
	 * 
	 * @param evtListener the listener
	 */
	public void addHistoryEventListener(HistoryEventListener evtListener) {
		eventListeners.add(evtListener);
	}

	/**
	 * Allow to fire the history event of the listeners
	 */
	private void fireHistoryEvent() {
		for (HistoryEventListener historyEventListener : eventListeners) {
			historyEventListener.historyEvent(stackPointer, actionsStack.size());
		}
	}

	/**
	 * Get instance of the history for the program
	 * 
	 * @return the instance of the history
	 */
	public static ActionsHistory getInstance() {
		return INSTANCE;
	}
}
