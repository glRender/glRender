node {
    stage('clone') {
		    checkout scm
	  }	
    stage('prepare_env_in') {
        sh 'scenarist.py run prepare_env_in:dockerImage=\"ubuntu:16.04\"'
    }
    stage('build') {
        sh 'scenarist.py run build_in:dockerImage=\"ubuntu:16.04\"'
    }
    stage('unit_tests') {
        sh 'scenarist.py run unit_tests_in:dockerImage=\"ubuntu:16.04\"'
    }
    stage('make_package') {
        sh 'scenarist.py run make_package_in:dockerImage=\"ubuntu:16.04\"'
    }
}